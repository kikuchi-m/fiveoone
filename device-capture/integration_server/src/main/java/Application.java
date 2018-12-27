package jp.co.atware.fiveoone;

import jp.co.atware.fiveoone.leap.Leap;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class Application {
    public static void main(String... args) {

        try (DatagramChannel channel = DatagramChannel.open()) {
            channel.socket().bind(new InetSocketAddress("localhost", 22043));
            ByteBuffer buf = ByteBuffer.allocate(4096);
            Leap.Frame frame;

            while (true) {
                buf.clear();

                channel.receive(buf);
                buf.flip();

                frame = Leap.Frame.parseFrom(buf);
                System.out.println("received (" + buf.limit() + "): "
                        + frame.getId() + " " + frame.getTimestamp()
                        // + " L: "
                        // + frame.getLeftHand() + ", R: " + frame.getRightHand()
                        );
            }
        } catch (Exception e) {
            System.out.println("ERROR: " + e);
            e.printStackTrace();
        }
    }
}
