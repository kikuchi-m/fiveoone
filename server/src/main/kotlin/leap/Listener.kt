package jp.co.atware.fiveoone.server.leap

import jp.co.atware.fiveoone.leap.Leap

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.DatagramChannel

class Listener(val onEvent: (MotionEvent) -> Unit) {
    private var prevFrame: Leap.Frame? = null

    fun start() {
        DatagramChannel.open().use { channel ->
            channel.socket().bind(InetSocketAddress("localhost", 22043))
            var buf = ByteBuffer.allocate(4096)

            while (true) {
                buf.clear()

                channel.receive(buf)
                buf.flip()

                val frame = Leap.Frame.parseFrom(buf)
                // println("received (${buf.limit()}): ${frame.id} ${frame.timestamp} ${frame.swipeGesturesCount}")
                handle(frame)
            }
        }
    }

    // TODO:
    private fun handle(frame: Leap.Frame) {
        if (frame.swipeGesturesCount == 0) {
            return
        }
        val currentState = frame.swipeGesturesList[0].state
        val prev = prevFrame
        if (prev != null) {
            if (prev.swipeGesturesCount == 0 || prev.swipeGesturesList[0].state != currentState) {
                val diff = frame.timestamp - prev.timestamp
                println(diff)
                if (diff > 3 * 1000L) {
                    onEvent(MotionEvent(currentState))
                }
            }
        } else {
            onEvent(MotionEvent(currentState))
        }
        prevFrame = frame
    }
}
