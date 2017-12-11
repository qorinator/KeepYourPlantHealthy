var ContentUpdater = {};

ContentUpdater.Update = function (select) {
	ContentUpdater.UpdateDateDisplay(select);
	ContentUpdater.UpdateChart(select);
}

ContentUpdater.UpdateDateDisplay = function(select) {
	switch(select) {
		case "Daily":			
			DateJs.DisplayDay(DateUpdater.current);
			break;
		case "Weekly" :
			DateJs.DisplayWeek(DateUpdater.current);
			break;
	}	
};

ContentUpdater.UpdateChart = function(select) {	
	switch(select) {
		case "Daily":			
			DailyUpdater.Update();
			break;
		case "Weekly":
			SensorChartUpdater.Update();			
			break;
	}
};