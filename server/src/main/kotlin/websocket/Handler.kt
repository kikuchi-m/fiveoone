package jp.co.atware.fiveoone.server.controller

import jp.co.atware.fiveoone.server.leap.MotionEvent
import jp.co.atware.fiveoone.server.leap.MotionEventProvider
import org.springframework.context.annotation.Configuration
import org.springframework.web.socket.CloseStatus
import org.springframework.web.socket.TextMessage
import org.springframework.web.socket.WebSocketSession
import org.springframework.web.socket.config.annotation.EnableWebSocket
import org.springframework.web.socket.config.annotation.WebSocketConfigurer
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry
import org.springframework.web.socket.handler.TextWebSocketHandler

@Configuration
@EnableWebSocket
class WebSocketConfig(val provider: MotionEventProvider) : WebSocketConfigurer {

    private val handler = SocketHandler();
    private val subscriptoinId = provider.subscribe(handler::broadcast)

    override fun registerWebSocketHandlers(registry: WebSocketHandlerRegistry) {
        registry.addHandler(handler, "/ws")
    }
}

class SocketHandler : TextWebSocketHandler() {
    private val sessions: MutableList<WebSocketSession> = mutableListOf()

    override fun afterConnectionEstablished(session: WebSocketSession) {
        super.afterConnectionEstablished(session)
        sessions.add(session)
        println("added (${sessions.size})");
    }

    override fun afterConnectionClosed(session: WebSocketSession, status: CloseStatus) {
        super.afterConnectionClosed(session, status)
        val removed = sessions.remove(session);
        println("removed with ${status} ${removed} (${sessions.size})");
    }

    override fun handleTextMessage(session: WebSocketSession, message: TextMessage) {
        super.handleTextMessage(session, message)
        println(message);
    }

    fun broadcast(event: MotionEvent) {
        sessions.forEach {
            it.sendMessage(TextMessage("""{ "gestureState": "${event.gestureState}" }"""))
        }
    }
}
