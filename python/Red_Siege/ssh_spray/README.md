# Brute Force - Project 3

## Scenario

You are working on an internal penetration test and have found a system that your point of contant labeled as "mission critical"
has SSH enabled. Due to other findings on the network you know the security administrator has weak passwords on lots of critical systems.
Knowing this, you believe that you can password sparay/brute force you way to victory.

## Beginner

Write a script that will perform a password spray against the SSH service using a single username and a password list. It should output
each time a username/password combination fails, and stop on success.

## Intermediate

Give your script the added functionality to spray using a list of usernames and a single password, using lists for both user name and password, and a traditional
brute force option.

## Expert

Add the option to limit the login attempts based on a timer. Example, run 5 login attempts - wait 60 seconds, repeat.

## Test Environment

You will need a local VM with SSH enabled for testing, or you can set up a VPS with Digital Ocean/AWS for the experience.
