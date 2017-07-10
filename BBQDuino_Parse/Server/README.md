# Startup

npm install
node server.js

# Credentials

Need to be in the credentials.json file

# Parse Cloud Code

Install parse tools - `curl -s https://www.parse.com/downloads/cloud_code/installer.sh | sudo /bin/bash`

Navigate to `cd ./cloud`

Setup account key `parse configure accountkey`

Run `parse new`

New/Existing/Select App/Choose Dir

Navigate to chosen dir `cloud/main.js`

Edit code

Run `parse deploy` to push to parse

////////////////////////////////////////////////////////////

Next, you might want to deploy this code with:

    cd C:\Users\Brian_2\Documents\Arduino\GrillLog\Server\cloud\GrillLog\cloud\GrillLog
    b4a deploy

Once deployed you can test that it works by running:
curl -X POST \
 -H "X-Parse-Application-Id: ryoXsXg0mMCvqcQMJgOYMIIfA6td2IaKEjM8SmV6" \
 -H "X-Parse-REST-API-Key: 4eoGAHuEwVncZnUiY9t9IUFd6sjxEW7RTdHaAV3w" \
 -H "Content-Type: application/json" \
 -d "{}" \
 https://parseapi.back4app.com/functions/hello

 https://www.back4app.com/