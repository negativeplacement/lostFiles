# CookBook Pro

This is a web app for meal planning and finding recipes built using React, Bootstrap, and Firebase. 

## Features (Some in development)

- Browse recipes by ingredient, cuisine type, dietary needs, etc
- Save recipes to weekly meal plans
- Generated grocery lists from planned recipes
- View detailed info and instructions for each recipe
- Add your own recipes to the app

## Usage

To use this app, you will need to obtain your own API key for the Spoonacular API and add it to the environment. 

### Obtain API Key

1. Go to [spoonacular.com](https://spoonacular.com/) and sign up for an account
2. Navigate to My Console > API Key and copy your personal API key

### Configure Environment 

1. Create a `.env` file in the root directory
2. Add the following variable, replacing `<your_api_key>` with your key:

```
REACT_APP_SPOONACULAR_API_KEY=<your_api_key>
```

### Run the App

1. `npm install` to install dependencies
2. `npm start` to run the development server
3. Visit `http://localhost:3000` in your browser

Now you can use all the features of the app! As you interact with recipes, your usage will be counted against your allotted Spoonacular API quota.

## Technologies Used

- React - Front end framework
- Bootstrap - CSS styling
- Firebase - Back end database for storing user data
- Spoonacular API - Provides recipe data 
