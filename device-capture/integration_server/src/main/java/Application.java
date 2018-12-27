package jp.co.atware.five_o_one;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class Application {
    public static void main(String... args) {

        try (DatagramChannel channel = DatagramChannel.open()) {
            channel.socket().bind(new InetSocketAddress("localhost", 22043));
            ByteBuffer buf = ByteBuffer.allocate(4096);

            while (true) {
                buf.clear();

                channel.receive(buf);
                buf.flip();

                System.out.println("received (" + buf.limit() + ")");
            }
        } catch (Exception e) {
            System.out.println("ERROR: " + e);
            e.printStackTrace();
        }
    }
}
