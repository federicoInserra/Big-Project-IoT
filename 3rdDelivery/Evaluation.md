#EVALUATION

## User experience point of view

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

### KPI
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
The costs remained the same as calculated in the previous document:

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

### Older version

- [Evaluation at first delivery](https://github.com/federicoInserra/Big-Project-IoT/blob/master/2stDelivery/Evaluation.md)
