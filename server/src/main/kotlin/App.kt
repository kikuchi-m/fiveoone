package jp.co.atware.fiveoone.server

import jp.co.atware.fiveoone.server.leap.LeapConsumer
import jp.co.atware.fiveoone.server.leap.MotionEventProvider
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.context.event.ApplicationReadyEvent
import org.springframework.context.ApplicationListener
import org.springframework.context.annotation.Bean
import org.springframework.stereotype.Component

@SpringBootApplication
class App

@Component
class OnStartUpLister : ApplicationListener<ApplicationReadyEvent> {

    private val leapConsumer = LeapConsumer()

    override fun onApplicationEvent(event: ApplicationReadyEvent) {
        println("--- on startup ---")
        leapConsumer.start()
    }

    @Bean
    fun provideEventProvider(): MotionEventProvider {
        println("--- providing MotionEventProvider ---")
        return leapConsumer
    }
}

fun main(args: Array<String>) {
    SpringApplication.run(App::class.java, *args)
}
