var ContentUpdater = {};

ContentUpdater.Update = function (select) {
	ContentUpdater.UpdateDateDisplay(select);
	ContentUpdater.UpdateChart(select);
}

ContentUpdater.UpdateDateDisplay = function(select) {
	switch(select) {
		case "Daily":			
			document.getElementById('dateDisplay').innerHTML = DateUpdater.GetDisplay();
			break;		
	}
	
};

ContentUpdater.UpdateChart = function(select) {	
	switch(select) {
		case "Daily":			
			ChartUpdater.Update();
			break;
		case "Weekly":
			SensorChartUpdater.Update();			
			break;
	}
};