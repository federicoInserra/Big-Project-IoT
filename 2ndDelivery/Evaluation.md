# Evaluation 


## User experience point of view
Our aim is to involve the people who visit the museum by making them actively participate with the statues and the surrounding environment.
At the same time we would like to introduce them to the true appearance of the statues with their original colours.
We have chosen to use holograms because we think it is an uncommon experience that can entertain people while they are learning something. 


### How to evaluate our system
First of all we did short interviews with users to see if using holograms would be fun.
From these interviews we found out that users think that holograms would enrich the visit a lot.
Also, most of them didn't know that the statues were originally colored.
Almost all of the users would like to solve puzzles to make the hologram appear

### Interviews
#### Questions
<pre>
1) Are you interested in art?
2) How often do you visit a museum annually?
3) Did you know that originally the statues were colored and not white as they are now?
4) Would you like to see a reconstruction of the statues as they were originally? (so with colors and all the missing parts)?
5) Do you know what a hologram is?
6) Do you think you'd like to visit a museum more if in addition to seeing the ancient statues, you could see a hologram that
  represents the statues in their original shape and colors?
7) Would you find the visit more interesting if there were riddles to solve to show the hologram?

</pre>
#### Answers

##### User 1
<pre>
1) yes, pretty much
2) 2/3 times for year
3) No
4) Yes
5) Yes
6) Yes
7) Yes
</pre>

##### User 2
<pre>
1) yes
2) 1/2 times for year
3) No, I didn't know
4) Yes, I'd like that.
5) More or less
6) Yes
7) Yes
</pre>


##### User 3
<pre>
1) yes, pretty much
2) 1 time for year
3) No, I didn't know
4) Yes, a lot
5) Yes
6) Absolutely Yes
7) Yes a lot
</pre>

##### User 4
<pre>
1) Not much
2) 0
3) Nope
4) yes
5) Yes
6) Yeah, I think it would be fun.
7) No, I think it's a bit challenging, if I can't find the right object after a while I get tired of it.
</pre>

##### User 5
<pre>
1) I'm mainly interested in classical art
2) Depends on exhibitions in general 2/3 times a year
3) I had no idea
4) yes
5) Yes
6) I think it would really enrich the visit
7) Yeah, I think it would be fun.
</pre>

##### User 6
<pre>
1) yes
2) 8 times for year
3) Yes, I knew it.
4) I'd love to
5) Yes, I know it
6) Yes
7) Yes
</pre>


### Tests
We have decided that in order to evaluate our system from a user experience point of view we will test it with real users.
In the meantime we will ask them questions about the experience and the actions they are doing to understand their emotions while using the system and if there are problems using it.
By doing the tests we will accumulate data and tips on user behavior that will allow us to further improve the experience.
Feedback from users will also be useful to understand if the experience will actually please users and if it will actually
be useful to increase visits to the museum.



## Technical point of view
From a technical point of view we want to evaluate two fundamental parameters: the cost of the entire infrastructure and the reactivity of the system.

### Cost of the system
The cost is estimated by calculating the cost of the NFC board and sensors and the approximate monthly cost of managing the cloud infrastructure with aws.

Unfortunately in our simulation we were not able to use a board that had a display so we simulated the display of the board with a raspberry pi that as soon as it received the signal from the board showed the image on the screen.


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




