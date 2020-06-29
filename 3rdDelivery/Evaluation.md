# EVALUATION

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
From these tests we want to understand if users prefer to interact with:
an app, using real objects or if they prefer the hologram to be projected constantly.

We took a sample of 16 people, divided in these age groups:
- 4 people between 11 and 14 now called 1st group
- 6 people between 15 and 24 now called 2nd group
- 6 people between 40 and 60 now called 3rd group

We chose the Think aloud method that is a user based evaluation method. In this technique, every user is encouraged to do a specific task and to comment what he/she is doing and why.
The experiment consisted in making each user try all three possibilities.

Type 1: interaction with objects
In this case we didn't have the possibility to use real objects with nfc code, so we simulated them by making the user choose an object and sending the signal using the phone.

Type 2: interaction using the app
Here the user uses an app to choose the hologram to show (In the app the statue to show is chosen and the phone is brought closer to the board. At this point the app will send the NFC code with the chosen statue and the hologram will appear).

Type 3: no interaction:
In this case the hologram was always projected and the user didn't have to do anything.

At the end of the evaluation this is what came out: 

The majority of the first group preferred the object interaction(3 over 4) mostly because they thought this interaction was more playful and it seemed like a game. The last user prefer to use the phone.

The second group was more toward the phone interaction because they think is more intuitive and says that your phone is always available while the object could be stolen or lost.
However, those who preferred interaction through objects said it was more satisfying than simply touching a screen.
Among six people four chose the phone and two the objects.

In the third group three of them didn't want to download an application to interact with a statue in the museum and prefer to try the object because they thought it was a different idea and they had not seen anything similar before.
Two of them prefer to use an app.
Only one user said that he would prefer to see the hologram without doing nothing to enjoy a more relaxing visit of the museum.

### KPIS
To define in a better way all the fundamental point of the user experience we have defined NUMBER of kpis:

KPI 1 User satisfaction:
With this KPI we want to monitor the level of user satisfaction with our product.
At the end of the tests we asked users to give a rating of 1-10 for the following categories:

Aesthetic effect of the hologram: average grade 9/10
Ease of use of the system: average grade 7/10
General impression on the product: average grade 8/10


KPI 2 Number of visit at museum:
We want to monitor whether our idea is effective and able to bring more visits to the museum.
If it is implemented this kpi will analyse the number of people who have visited the museum comparing them with the numbers of the past years when the museum had not implemented our idea.
A possible increase in the number of visits would show the real usefulness of our idea.


KPI 3 Actual usage:
This KPI monitors how often people interact with the board to see the hologram.
For this reason every time there is an interaction with the board, it sends the data to a database that collects statistics on the statues.



## Technical point of view
From a technical point the most important parameters to evaluate are the cost of the entire infrastructure and the reactivity of the system.

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
---------------------------------DA FARE!!!



### KPIS 
Also to evaluate the architecture we have defined KPIs that allow us to monitor the fundamental parameters of our infrastructure.

KPI 1 Privacy of the users:
Our architecture guarantees total user privacy.
No personal data of the user will be saved, processed or modified, the only data saved will be those related to the object that interacts with the board (e.g. time, type of interaction, object name, etc.).

KPI 2 Data security:
All data is stored in an AWS database, which guarantees high security.

KPI 3 Reactivity of the system:
It is important that users have the best possible experience when using the system.
To ensure this, this KPI is defined to monitor the speed of the system.
In particular it analyzes the time that passes from the moment the board receives the object's nfc signal to when the hologram is visible to the user.
It also takes into account the time needed to make this data available to the curators.


KPI 4 Cost of the system:
Cost is another key parameter to take into account for a successful application.
An elevated cost for maintaining the infrastructure could not be sustainable by the museum.


### Older version

- [Evaluation at Second delivery](https://github.com/federicoInserra/Big-Project-IoT/blob/master/2stDelivery/Evaluation.md)
