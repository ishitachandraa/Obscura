import speech_recognition as sr
import serial
import time

# Initialize the serial connection to Arduino
# Replace 'COM3' with the port where your Arduino is connected
arduino = serial.Serial('/dev/tty.usbmodem101', 9600)  # Use the correct COM port for your system
time.sleep(2)  # Wait for the connection to initialize

# Initialize the speech recognizer
recognizer = sr.Recognizer()

print("Listening for the secret phrase: 'read'")

while True:
    try:
        # Use the default microphone as the audio source
        with sr.Microphone() as source:
            print("Say something...")
            audio = recognizer.listen(source)

        # Recognize speech using Google Web Speech API
        text = recognizer.recognize_google(audio).lower()
        print(f"You said: {text}")

        # Check if the secret phrase is detected
        if "read" in text:
            print("Secret phrase detected!")
            arduino.write(b'1')  # Send the signal '1' to Arduino via serial
            time.sleep(1)  # Add a small delay to prevent multiple triggers
            break  # Exit the loop after sending the signal

    except sr.UnknownValueError:
        print("Sorry, I couldn't understand what you said.")
    except sr.RequestError as e:
        print(f"Could not request results; {e}")
