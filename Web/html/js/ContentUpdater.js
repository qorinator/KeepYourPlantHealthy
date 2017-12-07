var ContentUpdater = {};

ContentUpdater.Update = function (select) {
	ContentUpdater.UpdateDateDisplay();
	ContentUpdater.UpdateChart(select);
}

ContentUpdater.UpdateDateDisplay = function() {
	document.getElementById('dateDisplay').innerHTML = DateUpdater.GetDisplay();
};

ContentUpdater.UpdateChart = function(select) {	
	switch(select) {
		case "Daily":			
			ChartUpdater.Update();
		break;
		case "Weekly":
			console.log("Weekly update");
		break;
	}
};