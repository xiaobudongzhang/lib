<?php
print_r($_GET);

$url="https://github.com/login/oauth/access_token";//post 

/* Name	Type	Description
client_id	string	Required. The client ID you received from GitHub when you registered.
client_secret	string	Required. The client secret you received from GitHub when you registered.
code	string	Required. The code you received as a response to Step 1.
redirect_uri	string	The URL in your application where users will be sent after authorization. See details below about redirect urls.
state	string	The unguessable random string you optionally provided in Step 1. */