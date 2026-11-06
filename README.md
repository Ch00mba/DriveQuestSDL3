# Report

[YouTube Link](https://youtu.be/cwWaIFrFbRE)

## Original Proposal
<img width="791" height="887" alt="image" src="https://github.com/user-attachments/assets/ab483b9c-83b0-40da-a20d-dc946102355a" />

In my original proposal it was intended to include a timer when in the quiz state of the game. This unfortunately had to be cut due to timing and difficulty with animation, instead the quiz remains on the screen until the player provides an answer. The game also had to be altered so that instead of using a style where you can see the future road ahead and looking from the rear of the player car, we instead just have a traditional top-down view.

Overall, the game turned out as what I had visioned minus the few changes made as mentioned prior, I stuck to the proposal relatively strictly.

## Gameplay description
The game is played using the arrow keys on a standard keyboard, this is to ensure anyone, even those with no background in PC gaming who won't know the standard controls can play the game. The game was made for people to learn basic road rules via playing a driving simulator type game. so the player move along an infinite road and every 15 seconds, a quiz will appear that the player must answer correctly or the game will fail.

## Game Mechanics and Code
The game was programmed using C++ with the SDL3 library, the game runs using the standard window that SDL3 offers, resized to 600x900 pixels to have a tall, similar to a mobile shape, aspect ratio.

<img width="508" height="98" alt="window snippet" src="https://github.com/user-attachments/assets/0a83ea56-42c2-400c-96a8-8cffae98fcd2" />

The movement of the vehicle is only left and right but the background scrolls down, providing the illusion that the car is moving along a road.

<img width="406" height="140" alt="movement state" src="https://github.com/user-attachments/assets/026f7eb2-35e4-4f3f-b6f9-c2bdba3720c9" />

The movement is handled via SDL's keyboard state command

<img width="363" height="93" alt="image" src="https://github.com/user-attachments/assets/58e49be7-1ac8-4b29-bced-95b59199d665" />
<img width="580" height="135" alt="image" src="https://github.com/user-attachments/assets/1e793421-7b8d-4d34-bfec-28f21bbd421c" />

The moving background is handled through iterating the background every frame and if it gets past a certain point it will create a new road and infinitely repeat it above the displayed one.

## Dependencies
The only dependency the game has is SDL3, but seeing as its handled by CMake, installation of SDL3 onto the user's system is not required.

## AI Development Log
There were many uses of AI when developing the game, although I have tried to keep it my own the best I can. 

#### ChatGPT:
ChatGPT's main role was asset creation. ChatGPt was used to make:
<li>Road Background</li>
<li>Car Sprite</li>
<li>Speed limit sign</li>

All other in game assets where made by me.

#### Gemini:
I utilized Gemini's Pro Model to handle the code-related aspects:
<li>Generated the SDL3 game boilerplate code excluding the window creation</li>
<li>Generated the CMake files to successfully run SDL3 without installation</li>
<li>Assistive role when I used wrong/outdated SDL tools</li>
<li>help with importing a BMP image and color-keying out the background</li>

When using Gemini for concepts I was stuck on, I requested it guide me through how to do things, without providing me with any code at all.

Examples of AI usage:

<img width="741" height="734" alt="image" src="https://github.com/user-attachments/assets/434b4b19-60e8-4775-ba3b-53c1a1acc119" />

<img width="741" height="705" alt="image" src="https://github.com/user-attachments/assets/562cd19e-787c-4353-89cb-a96b45c2622b" />

the prompts used were originally for a 2.5D from a car perspective, which was later ditched.

<img width="652" height="599" alt="image" src="https://github.com/user-attachments/assets/72862fd4-7fce-4f9f-9a3a-483e3c3c4d04" />

ChatGPT had a hard time making images transparent on the first prompts.

<img width="829" height="856" alt="image" src="https://github.com/user-attachments/assets/37f2dca8-a970-404f-9ddc-a41adf0aa360" />

<img width="923" height="693" alt="image" src="https://github.com/user-attachments/assets/f5e5e7c1-6ab5-45cc-a279-0b49d7e9d88d" /> <img width="810" height="229" alt="image" src="https://github.com/user-attachments/assets/a4383a58-002a-4634-b7d5-f541c717cc21" />

Gemini had assumed I wanted the CMake files for an installed version of SDL3

<img width="795" height="774" alt="image" src="https://github.com/user-attachments/assets/d0ce3254-e95d-418d-8212-6f665a9ac04f" />

The CMake files it originally gave caused an error where the C++ file couldn't launch due to a dll not being found, so Gemini utilized a newer version of CMake

<img width="873" height="595" alt="image" src="https://github.com/user-attachments/assets/798c633c-c47c-4d88-9896-11fe3cf2b5cb" />

I asked Gemini for a theoretical response on how to make controlled movement.

<img width="885" height="764" alt="image" src="https://github.com/user-attachments/assets/d76aa37b-1164-490c-bbde-f483e03c7f68" />

This prompted me to research keydown events and DetaTime.

<img width="553" height="246" alt="image" src="https://github.com/user-attachments/assets/8d662a5f-d26e-4d91-ba54-fbd0be58802d" />

I used an outdated method and asked it to debug for me.

<img width="820" height="432" alt="image" src="https://github.com/user-attachments/assets/408de962-1ca9-4752-8cf2-978bfc18a258" />
<img width="793" height="404" alt="image" src="https://github.com/user-attachments/assets/c61dd33d-7030-4108-a1d3-29448065311c" />

## UML Diagrams
I created UML diagrams to show how the game should look, only some changes were made to this, such as the countdown timer on quizzes, and the camera style

<img width="356" height="228" alt="image" src="https://github.com/user-attachments/assets/057aca26-6bd0-4828-94a0-7b13ecec2244" />
<img width="368" height="201" alt="image" src="https://github.com/user-attachments/assets/7e742419-c299-403d-8148-ad250b300e98" />

## Sample Screens
<img width="597" height="935" alt="image" src="https://github.com/user-attachments/assets/f514325f-188c-4005-939d-88b49aa2365c" />

<img width="486" height="726" alt="image" src="https://github.com/user-attachments/assets/25c3b747-eec0-44f6-a59a-f4fa287bc93b" />

<img width="238" height="34" alt="image" src="https://github.com/user-attachments/assets/2a65d72f-2dee-402a-96f1-b259c8ec546c" />

<img width="396" height="755" alt="image" src="https://github.com/user-attachments/assets/9e512399-1dff-47ef-806b-11607d53b56a" />

<img width="450" height="30" alt="image" src="https://github.com/user-attachments/assets/2f67e2c7-0bf2-4482-a201-8c3409618762" />

## Evaluation
Overall I am happy with how the game turned out, I am happy that I have managed to create a working prototype of a game that is built only using C++ with no game engine, a lot of the documentation is old/outdated and hard to find so I am glad I didn't give up. what I would try and do differently next time is find a way to have transparent images work without having to color-key out the background, this sometimes leaves a faint outline around the assets.












