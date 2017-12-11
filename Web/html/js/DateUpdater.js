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

DateUpdater.IncreaseWeek = function() {
	if(DateUpdater.current >= DateUpdater.todayDate)
		DateUpdater.current.setDate(DateUpdater.todayDate.getDate());
	else
		DateUpdater.current.setDate(DateUpdater.current.getDate() + 7);
	DateJs.DisplayWeek(DateUpdater.current);
};

DateUpdater.DecreaseWeek = function() {
	DateUpdater.current.setDate(DateUpdater.current.getDate() - 7);
	DateJs.DisplayWeek(DateUpdater.current);
};