# Project 2 - Web Header Reporting

## Scenario

Red Planet has assigned you to do a web application penetration test against a few target domains.
There are a few findings you team regularly reports on, but are not very fun to detect or write up.
As such, you are looking to automate this portion of your test so you can spend more time on critical
items.

### Beginner

Write a script that will have the user input a HTTPS URL. The script should pull down the web headers
for the URL, and report back if the `Strict-Transport-Security` header is missing.

### Intermediate

Have the script run multiple URLs from a file and process them. Additionally, have it output both the URL
and IP address for each URL missing the `Strict-Transport-Security` header.

### Expert

Have the script perform all of the above tasks, but also check for the `Content-Security-Policy` and 
`X-Frame-Options` headers and report if missing. If the `Server` header is present, the value of the header
should be returned.

### Bonus

Have the script evaluate if the URL is HTTP or HTTPS. If HTTP, ignore the need for `Strict-Transport-Security` header
, but evaluate other criteria.

