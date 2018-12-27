package jp.co.atware.fiveoone.server.leap

import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.atomic.AtomicLong

import kotlinx.coroutines.*

interface MotionEvent {
}

interface MotionEventProvider {
    fun subscribe(action: (MotionEvent) -> Unit): Long
    fun unsubscribe(id: Long): Boolean
}

class LeapConsumer : MotionEventProvider {
    // TODO: prepare subscription object
    private val currentId = AtomicLong(0)
    private val map = ConcurrentHashMap<Long, (MotionEvent) -> Unit>()
    private var leapListenJob: Job? = null

    fun start() {
        println("--- start listening UDP ---")
        if (leapListenJob?.isActive ?: false) {
            println("*** already started listening ***")
        } else {
            leapListenJob = GlobalScope.launch {
                try {
                    Listener().start()
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
        map.put(subscriptionId, action)
        return subscriptionId
    }

    override fun unsubscribe(id: Long): Boolean = map.remove(id) != null
}

