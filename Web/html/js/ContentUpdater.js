var ContentUpdater = {};

ContentUpdater.Update = function (select) {
	ContentUpdater.UpdateDateDisplay(select);
	ContentUpdater.UpdateChart(select);
}

ContentUpdater.UpdateDateDisplay = function(select) {
	switch(select) {
	case "Daily":			
		DateJs.DisplayDay();
		break;
	case "Weekly" :
		DateJs.DisplayWeek();
		break;
	case "Monthly" :
		DateJs.DisplayMonth();
		break;
	}	
};

ContentUpdater.UpdateChart = function(select) {	
	switch(select) {
	case "Daily":			
		DailyUpdater.Update();
		break;
	case "Weekly":
		WeeklyUpdater.Update();			
		break;
	case "Monthly" :
		MonthlyUpdater.Update();
		break;
	}
};