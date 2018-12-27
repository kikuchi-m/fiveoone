package jp.co.atware.fiveoone.server.leap

import jp.co.atware.fiveoone.leap.Leap

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.DatagramChannel

class Listener {

    fun start() {
        DatagramChannel.open().use { channel ->
            channel.socket().bind(InetSocketAddress("localhost", 22043))
            var buf = ByteBuffer.allocate(4096)

            while (true) {
                buf.clear()

                channel.receive(buf)
                buf.flip()

                val frame = Leap.Frame.parseFrom(buf)
                println("received (${buf.limit()}): ${frame.id} ${frame.timestamp} ${frame.swipeGesturesCount}")
            }
        }
    }
}
