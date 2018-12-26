package sample;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class UdpServer {

    public static void main(String... args) {

        try (DatagramChannel channel = DatagramChannel.open()) {
            channel.socket().bind(new InetSocketAddress("localhost", 22043));
            ByteBuffer buf = ByteBuffer.allocate(1024);

            while (true) {
                buf.clear();

                channel.receive(buf);
                buf.flip();

                Sample.Greeting msg = Sample.Greeting.parseFrom(buf);
                System.out.println("received (" + buf.limit() + "): "
                        + msg.getId() + " " + msg.getGreetingMessage());

            }
        } catch (Exception e) {
            System.out.println("ERROR: " + e);
            e.printStackTrace();
        }
    }
}
