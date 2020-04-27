### EVALUATION DOCUMENT

## User experience point of view
Our goal is to create an app that can entice people (especially teenagers and young adults) to visit the museum to learn more and live a more interactive visiting experience.
In addition, the app aims to collect data in order to provide museum curators with information on the areas that users find more interesting than the others.

We decided to evaluate our app from the user point of view with the following KPIs.


## KPI 1: 
Number of users theoretically interested in the app.
We can take this data from the questionnaires we are doing these days, and it allows us to see if users are actually interested in the app.
We expect that at least 60% of the users who answer the questionnaire give us a positive opinion on our idea.

## KPI 2:
Number of app downloads for museum visits, given by the formula: (N_download_app/N_visitors) this allows us to assess how much our app is actually deemed to be useful and able to improve users' visit to the museum.
We expect at least 5 out of 10 visitors to download our app.
If at least half of the visitors of the museum downloads the app, we can provide a more accurate estimate of the most interesting areas, as it is likely that if a user is interested in a certain area, they will participate in the quiz related to that area.

## KPI 3:
Another important factor to evaluate is the average percentage of areas completed in the quiz.
In fact, if a user completes the quiz only for one or two zones, he probably doesn't find the quiz interesting or engaging enough.
On the contrary, if a user completes at least 60% of the zones in the quiz, it means that they think the experience provided by the quiz is positive.

## KPI 4:
Targeting mainly teenagers and partly young adults one of the parameters to be measured will be the increase in visits by schoolchildren at the museum. 
As we believe that for high school professors to allow the students to participate in a quiz on the museum could entice the students to learn more about the museum's works, and in case  to reward the students who ranked best at the end of the trip.
It would also allow the students to live the trip differently, having fun and competing with each other to win the quiz.
That's why a 10% increase in school trips to the museum might prove that the idea is successful.




### Technical point of view
From a technical point of view, our goal is to create a relatively simple structure that allows users to enjoy the experience in the best possible way while respecting their privacy and security, and at the same time allowing museum curators not to incur excessive costs to maintain the infrastructure.

For this reason we will use the following KPIs to monitor the parameters.


## KPI 1:
High level of privacy.
We would like to design our app in a way that we do not save any kind of personal user data in a persistent way.
The idea is to ask the user only for a username to which will be linked all the few "sensitive" data required (such as the time of entry and exit from the museum).
In this way it will not be possible to trace the real user in any way, unless we know exactly the username he chose, and even then, the only information available would be the user's final score in the quiz.

## KPI 2:
Data security.
The data will be saved on a database managed by Google in its cloud platform, which guarantees high security.
As you can read from the Google cloud site in the section on data storage:

"Data stored on our infrastructure is automatically encrypted at rest and distributed for availability and reliability. 
This helps guard against unauthorized access and service interruptions."

## KPI 3:
In order for users to have the best possible experience it is necessary that the app responds quickly to the user's requests (e.g. showing the questions or checking the answers).
For this reason the app must be able to show all the requested data on screen within one second.
In addition, the server must be able to handle up to 100 users simultaneously.

## KPI 4:
Cost is another key parameter to be taken into account for a successful application.
In fact, an elevated cost for maintaining the infrastructure could not be sustainable by the museum.
We think that a cost of less than 10€ per month is necessary to guarantee the management of the infrastructure to the museum without problems.
We have estimated that the total cost of maintaining the database and the server to manage the requests using Google cloud platform will be around 7€ per month.


