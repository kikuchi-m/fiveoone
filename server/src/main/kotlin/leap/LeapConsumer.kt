package jp.co.atware.fiveoone.server.leap

import jp.co.atware.fiveoone.leap.Leap

import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.atomic.AtomicLong

import kotlinx.coroutines.*

// TODO: update (interim implementation)
class MotionEvent(val gestureState: Leap.GestureState)

interface MotionEventProvider {
    fun subscribe(action: (MotionEvent) -> Unit): Long
    fun unsubscribe(id: Long): Boolean
}

class LeapConsumer : MotionEventProvider {
    // TODO: prepare subscription object
    private val currentId = AtomicLong(0)
    private val handlers = ConcurrentHashMap<Long, (MotionEvent) -> Unit>()
    private var leapListenJob: Job? = null

    fun start() {
        println("--- start listening UDP ---")
        if (leapListenJob?.isActive ?: false) {
            println("*** already started listening ***")
        } else {
            leapListenJob = GlobalScope.launch {
                try {
                    Listener(::onEvent).start()
                } catch (e: Exception) {
                    println(e)
                }
            }
            println("--- started listening UDP ---")
        }
    }

    fun stop() {
        leapListenJob?.cancel()
        println("--- stop listening UDP ---")
    }

    override fun subscribe(action: (MotionEvent) -> Unit): Long {
        println("--- registering event handler ---")
        val subscriptionId = currentId.incrementAndGet()
        handlers.put(subscriptionId, action)
        return subscriptionId
    }

    override fun unsubscribe(id: Long): Boolean = handlers.remove(id) != null

    fun onEvent(event: MotionEvent) {
        handlers.forEach { _, a -> a(event) }
    }
}

