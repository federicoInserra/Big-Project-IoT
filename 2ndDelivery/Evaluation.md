# Evaluation 


## User experience point of view
Our aim is to involve the people who visit the museum by making them actively participate with the statues and the surrounding environment.
At the same time we would like to introduce them to the true appearance of the statues with their original colours.
We have chosen to use holograms because we think it is an uncommon experience that can entertain people while they are learning something. 


### How to evaluate our system
We have decided that in order to evaluate our system from a user experience point of view we will test it with real users.
In the meantime we will ask them questions about the experience and the actions they are doing to understand their emotions while using the system and if there are problems using it.
By doing the tests we will accumulate data and tips on user behavior that will allow us to further improve the experience.
Feedback from users will also be useful to understand if the experience will actually please users and if it will actually
be useful to increase visits to the museum.



## Technical point of view
From a technical point of view we want to evaluate two fundamental parameters: the cost of the entire infrastructure and the reactivity of the system.

### Cost of the system
The cost is estimated by calculating the cost of the NFC board and sensors and the approximate monthly cost of managing the cloud infrastructure with aws.

Unfortunately in our simulation we were not able to use a board that had a display so we simulated the display of the board with a raspberry pi that as soon as it received the signal from the board showed the image on the screen. For this reason the total cost of the simulation is higher than the cost of a single board with nfc and integrated screen.


Cost simulation:
Board with integrated NFC and WIFI device = 57€
Programmable NFC stickers = 10€
raspberry pi 3 = 30€
monitor hdmi 5" = 35€

TOTAL = 132€ + approximate monthly AWS cost < 1€


Cost of the real system:
Board = 55€
NFC module = 16€
WIFI module = 21€
Screen and HDMI adapter = 55€ + 28€
Programmable NFC stickers = 10€
Simple objects representative of the statues:  Depends on the material from 2 to 15€ per object approx.

TOTAL = Around 195€ + Approximate monthly AWS cost < 1€




### Reactivity of the system
As far as the reactivity of the system is concerned, we want to evaluate it mainly on the basis of the speed at which the hologram appears from the moment we approach an object to the board.

As far as our simulation is concerned, the average times is 2,2 seconds from when you approach the object to when you see the image.




