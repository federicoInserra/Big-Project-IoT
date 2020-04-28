# EVALUATION DOCUMENT

## User experience point of view
Our goal is to create an app that can entice people in visiting the museum to learn more and live a more interactive visiting experience. Our targets are Teenagers and Young Adults.
The app aims to collect data to provide museum curators with information on the areas that users find more attractive than the others.

We decided to evaluate our app from the user point of view with the following KPIs.


### KPI 1: 
The number of users theoretically interested in the app.
We can get this data from the questionnaires we are doing these days, and it allows us to see if users are interested in the app.
We expect that at least 60% of the users who answer the questionnaire give us a positive opinion on our idea.

### KPI 2:
Usability Testing.
Usability testing is the observation of users trying to carry out tasks with a product. Testing can be focused on a single process or be much more wide-ranging.
In our case, we would like to develop a mockup of our app and observe the behavior of the users in doing the tasks (for example start the quiz).
In this way, we can decide if the interface we designed is usable or if we made mistakes in the design phase.

## Optional KPIs
We have also thought about other possible KPIs, but they can only be evaluated if the app is developed and integrated into the museum.

### KPI 3:
The number of app downloads for museum visits, given by the formula: (N_download_app/N_visitors) this allows us to assess how much our app is deemed to be useful and able to improve user's visit to the museum.
We expect 5 out of 10 visitors to download our app.
If at least half of the visitors of the museum downloads the app, we can provide a more accurate estimate of the most interesting areas, as it is likely that if a user is interested in a certain area, they will participate in the quiz related to that area.

### KPI 4:
Another important factor to evaluate is the average percentage of areas completed in the quiz.
If a user completes the quiz only for one or two zones, he probably doesn't consider the quiz interesting or engaging enough.
On the contrary, if a user completes at least 60% of the zones in the quiz, it means that they think the experience provided by the app is positive.

### KPI 5:
Targeting mainly teenagers and partly young adults, one of the parameters to be measured will be the increase in visits by schoolchildren at the museum. 
As we believe that for high school professors to allow the students to participate in a quiz on the museum could entice the students to learn more about the museum's works, and eventually to reward the students who ranked best at the end of the trip.
It would also allow the students to live the trip differently, having fun, and competing with each other to win the quiz.
That's why a 10% increase in school trips to the museum might prove that the idea is successful.




## Technical point of view
From a technical point of view, our goal is to create a simple structure that allows users to enjoy the experience in the best possible way. We also want to respect their privacy and security, and so, allowing museum curators not to incur excessive costs to maintain the infrastructure.

For this reason, we will use the following KPIs to monitor the parameters.


### KPI 1:
High level of privacy.
We would like to not save any kind of personal user data persistently in our app.
The idea is to ask the user only for a username to which will be linked all the few "sensitive" data required (such as the time of entry and exit from the museum).
In this way, it will not be possible to trace the real user in any way, unless we know exactly the username he chose, and even then, the only information available would be the user's final score in the quiz.

### KPI 2:
Data security.
The data will be saved on a database managed by Google in its cloud platform, which guarantees high security.
As you can read from the Google cloud site in the section on data storage:

"Data stored on our infrastructure is automatically encrypted at rest and distributed for availability and reliability. 
This helps guard against unauthorized access and service interruptions."

### KPI 3:
For users to have the best possible experience the app must respond quickly to the user's requests (e.g. showing the questions or checking the answers).
For this reason, the app must be able to show all the requested data on-screen within one second.
The server must be able to handle up to 100 users concurrently.

### KPI 4:
Cost is another key parameter to take into account for a successful application.
An elevated cost for maintaining the infrastructure could not be sustainable by the museum.
We think that a cost of less than 10€ per month is necessary to guarantee the management of the infrastructure to the museum without problems.
We have estimated that the total cost of maintaining the database and the server to manage the requests using the Google cloud platform will be around 7€ per month.

### KPI 5:
Given the current situation, we have decided that we can simulate the operation of our application using a board on IoT lab.
The idea is to program the board as if it were positioned in the museum and send the data to users' smartphones.
Once the board is active, we will show the data it sends to the screen and we will use one of our smartphones to simulate the real arrival of the data and make the user start the quiz as if he were really in the museum.

