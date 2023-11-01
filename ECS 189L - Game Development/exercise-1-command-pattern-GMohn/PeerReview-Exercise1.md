# Code Review for Programming Exercise 1 #
## Description ##

For this assignment, you will be giving feedback on the completeness of Exercise 1. In order to to do so, we will be giving you a rubric to give feedback on. For the feedback, please give positive criticism and suggestions on how to fix segments of code.

You only need to review code modified or created by the student you are reviewing. You do not have to review the code and project files that were given out by the instructor.

Abusive or hateful language or comments will not be tolerated and will result in a grade penalty or be considered a breach of the UC Davis Code of Academic Conduct.

If there are any questions at any point, please email the TA.

## Due Date and Submission Information ##

A successful submission should consist of a copy of this markdown document template that is modified with your peer-review. The file name should be the same as it is in the template: PeerReview-Exercise1.md. You also need to include your name and email address in the Peer-reviewer Information section below. This review document should be placed into the base folder of the repo you are reviewing in the master branch. This branch should be on the origin of the repository you are reviewing.

If you are in the rare situation where there are two peer-reviewers on a single repository, append your UC Davis user name before the extension of your review file. An example: PeerReview-Exercise1-username.md. Both reviewers should submit their reviews in the master branch.  

## Peer Reviewer Information ##
Reviewer Name: Hoai-An Ho

Reviewer Email: hoaho@ucdavis.edu

Reviewer GitHub: HoaiAnHo

## Solution Assessment ##

### Description ###

For assessing the solution, you will be choosing ONE choice from: unsatisfactory, satisfactory, good, great, or perfect. Place an x character inside of the square braces next to the appropriate label.

The following are the criteria by which you should assess your peer's solution of the exercise's stages.

#### Perfect #### 
    Can't find any flaws in relation to the prompt. Perfectly satisfied all stage objectives.

#### Great ####
    Minor flaws in one or two objectives. 

#### Good #####
    Major flaw and some minor flaws.

#### Satisfactory ####
    Couple of major flaws. Heading towards solution, however did not fully realize solution.

#### Unsatisfactory ####
    Partial work, not really converging to a solution. Pervasive Major flaws. Objective largely unmet.


### Stage 1 ###

- [x] Perfect
- [ ] Great
- [ ] Good
- [ ] Satisfactory
- [ ] Unsatisfactory

#### Justification ##### 
The player moves right and flips the sprite just as intended, no flaws found.

### Stage 2 ###

- [ ] Perfect
- [x] Great
- [ ] Good
- [ ] Satisfactory
- [ ] Unsatisfactory

#### Justification ##### 
Motivation scripts work as intended, but the items are instantiated at the center of the world (not at random), and there is no bounce/velocity to the items.

### Stage 3 ###

- [ ] Perfect
- [x] Great
- [ ] Good
- [ ] Satisfactory
- [ ] Unsatisfactory

#### Justifaction ##### 
Random.Range() only ever chooses values 1 and 2, never 3. Therefore, case 3 in the switch statement (FastWorkerPirateCommand) is never executed. Other than that, the random selection of pirate work commands (and the initial command being slow) is perfect.

### Stage 4 ###

- [x] Perfect
- [ ] Great
- [ ] Good
- [ ] Satisfactory
- [ ] Unsatisfactory

#### Justifaction ##### 
The main mechanic here is that the player can jump and dash in the direction they're facing. In that regard, this is executed as it was meant to do.

## Code Style ##

### Description ###
Check the scripts to see if the student code adheres to the dotnet style guide.

If there are sections that don't adhere to the style guide, please peramlink the line of code from Github and justify why the line of code has infractured the style guide.

It should look something like this:

* [description of infraction](https://github.com/dr-jam/ECS189L) - this is the justification.

Here is an example of the permalink drop down on Github.

![Permalink option](../images/permalink_example.png)

Here is another example as well.

* [I go to Github and look at the ICommand script in the ECS189L repo!](https://github.com/dr-jam/ECS189L/blob/1618376092e85ffd63d3af9d9dcc1f2078df2170/Projects/CommandPatternExample/Assets/Scripts/ICommand.cs#L5)

### Code Style Review ###

#### Style Guide Infractions ####
* [Brace use was off in the WorkerCommand scripts](https://github.com/ensemble-ai/exercise-1-command-pattern-GMohn/blob/master/Captain/Assets/Scripts/SlowWorkerPirateCommand.cs) - As seen in this example, some of the braces did not have their own line, like on lines 37, 44, and 49.

#### Style Guide Exemplars ####
* [Removal of default case in switch cases](https://github.com/ensemble-ai/exercise-1-command-pattern-GMohn/blob/master/Captain/Assets/Scripts/PirateController.cs) - All the cases for the switch statement are used (or at least attempted to be used). Nothing is wasted.

## Best Practices ##

### Description ###

If the student has followed best practices (Unity coding conventions from the StyleGuides document) then feel free to point at these segments of code as examplars. 

If the student has breached the best practices and has done something that should be noted, please add the infracture.

This should be similar to the Code Style justification.

* [description of infraction](https://github.com/dr-jam/ECS189L) - this is the justification.

### Best Practices Review ###

#### Best Practices Infractions ####
* Lots of empty spaces in some scripts. Should probably clean that up.

#### Best Practices Exemplars ####
* Documentation of intended effects of scripts. Keep up the commenting.
* [Efficient use of switch cases instead of if statements for the random WorkerCommand selection](https://github.com/ensemble-ai/exercise-1-command-pattern-GMohn/blob/master/Captain/Assets/Scripts/PirateController.cs) - 
