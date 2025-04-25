import React from 'react';

const MealPlans = () => {
    return (
        <div>
            <h1>Create a meal plan</h1>
            <div style={mealCategoryStyle}>
                <h2>Breakfast</h2>
                <div style={mealContainerStyle}>
                    <p>Placeholder for breakfast meal</p>
                    <div style={buttonContainerStyle}>
                        <button onClick={() => handleAddMeal('breakfast')}>Add</button>
                        <button onClick={() => handleRemoveMeal('breakfast')}>Remove</button>
                    </div>
                </div>
            </div>
            <div style={mealCategoryStyle}>
                <h2>Lunch</h2>
                <div style={mealContainerStyle}>
                    <p>Placeholder for lunch meal</p>
                    <div style={buttonContainerStyle}>
                        <button onClick={() => handleAddMeal('lunch')}>Add</button>
                        <button onClick={() => handleRemoveMeal('lunch')}>Remove</button>
                    </div>
                </div>
            </div>
            <div style={mealCategoryStyle}>
                <h2>Dinner</h2>
                <div style={mealContainerStyle}>
                    <p>Placeholder for dinner meal</p>
                    <div style={buttonContainerStyle}>
                        <button onClick={() => handleAddMeal('dinner')}>Add</button>
                        <button onClick={() => handleRemoveMeal('dinner')}>Remove</button>
                    </div>
                </div>
            </div>
        </div>
    );
};

const mealCategoryStyle = {
    marginBottom: '20px',
};

const mealContainerStyle = {
    border: '1px solid #ccc',
    padding: '10px',
    borderRadius: '8px',
    backgroundColor: '#f9f9f9',
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'space-between', // Add this line
};

const buttonContainerStyle = {
    display: 'flex',
    gap: '10px', // Add some space between buttons
};

const handleAddMeal = (mealType) => {
    // Placeholder function for adding a meal
    console.log(`Add ${mealType} meal`);
};

const handleRemoveMeal = (mealType) => {
    // Placeholder function for removing a meal
    console.log(`Remove ${mealType} meal`);
};

export default MealPlans;


