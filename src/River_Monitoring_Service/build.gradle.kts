/*
 * This file was generated by the Gradle 'init' task.
 *
 * This generated file contains a sample Java application project to get you started.
 * For more details take a look at the 'Building Java & JVM projects' chapter in the Gradle
 * User Manual available at https://docs.gradle.org/8.0.2/userguide/building_java_projects.html
 */

plugins {
    // Apply the application plugin to add support for building a CLI application in Java.
    id 'java-library'
}

repositories {
    // Use Maven Central for resolving dependencies.
    mavenCentral()
}

dependencies {
    // Use JUnit Jupiter for testing.
    testImplementation("org.junit.jupiter:junit-jupiter:5.9.1")

    // This dependency is used by the application.
    implementation("com.google.guava:guava:31.1-jre")
    // This dependency is exported to consumers, that is to say found on their compile classpath.
    api 'org.apache.commons:commons-math3:3.6.1'

    //mqtt dependencies
    implementation 'io.vertx:vertx-core:4.3.1'
    implementation 'io.vertx:vertx-web:4.3.1'
    implementation 'io.vertx:vertx-web-client:4.3.1'
    implementation 'io.vertx:vertx-mqtt:4.3.1'
    implementation group: 'com.fasterxml.jackson.core', name: 'jackson-databind', version: '2.14.2'

    // Use JUnit test framework
    testImplementation 'junit:junit:4.13.2'

	/* for logging */
	implementation 'org.slf4j:slf4j-api:1.7.25'
	implementation 'org.slf4j:slf4j-jdk14:1.7.36'
	
	//Gson libs
	implementation 'com.google.code.gson:gson:2.8.2'
	
	// https://mvnrepository.com/artifact/io.github.java-native/jssc
	implementation 'io.github.java-native:jssc:2.9.4'
}

tasks.named('test') {
    // Use JUnit Platform for unit tests.
    useJUnitPlatform()
}

application {
    // Define the main class for the application.
    mainClass.set("river_monitoring_service.RunService")
}

tasks.named<Test>("test") {
    // Use JUnit Platform for unit tests.
    useJUnitPlatform()
}
