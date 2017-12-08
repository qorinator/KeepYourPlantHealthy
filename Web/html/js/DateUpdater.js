var DateUpdater = {
	current: new Date(),
	todayDate: new Date()
};

DateUpdater.IncreaseDate = function() {
	if(DateUpdater.current >= DateUpdater.todayDate)
		DateUpdater.current.setDate(DateUpdater.todayDate.getDate());
	else
		DateUpdater.current.setDate(DateUpdater.current.getDate() + 1);
};

DateUpdater.DecreaseDate = function() {
		DateUpdater.current.setDate(DateUpdater.current.getDate() - 1);
};

DateUpdater.GetDisplay = function() {
	var output = DateUpdater.GetDay(DateUpdater.current.getDay()) + "   " + 
				 DateUpdater.GetMonthString(DateUpdater.current.getMonth()) + ' ' + 
				 DateUpdater.current.getDate() + ", " + 
				 DateUpdater.current.getFullYear();
	return output;
};

DateUpdater.GetMonthString = function(month) {
	var monthNames = ["January", "February", "March", "April", "May", "June", 
					  "July", "August", "September", "October", "November", "December"];
	return monthNames[month];
};

DateUpdater.GetDay = function(day) {
	var dayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
	return dayNames[day];
}

DateUpdater.IncreaseWeek = function() {
	if(DateUpdater.current >= DateUpdater.todayDate)
		DateUpdater.current.setDate(DateUpdater.todayDate.getDate());
	else
		DateUpdater.current.setDate(DateUpdater.current.getDate() + 7);
	NextWeek();
};

DateUpdater.DecreaseWeek = function() {
	DateUpdater.current.setDate(DateUpdater.current.getDate() - 7);
	PreviousWeek();
};