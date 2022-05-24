# EditableClock
An editable clock made in C for one of my classes called "Digital circuits and microcontrollers". My partner and I, programed the micro known as "atmega328p". The outputs we used were an lcd (to show the time and date) and a keypad (to realize changes).
Here is a screenshot of the componentes and conexions in proteus


![image](https://user-images.githubusercontent.com/55964645/170051154-f9ee6022-fe27-43d0-8e99-b9c655b515a7.png)

How it works?


You can use all the keypad but the keys that do something are
- 'A': Edit mode, you go through year to seconds, if you are in seconds and all the changes are okay -> Congratulations that's your new date and time and the clock continues running.
- 'B': Increment actual value.
- 'C': Decrement actual value.
- 'D': Cancel operation.


When you press the 'A' key the clock that is showned in the display stops, but the intern clock don't so if you cancel the operation you will see the intern clock value (with the time that has passed after you freezed the clock to edit).

It's easier to understand if you try it, go ahead! (Probably you'll have to change the path in the microcontroller of proteus).
