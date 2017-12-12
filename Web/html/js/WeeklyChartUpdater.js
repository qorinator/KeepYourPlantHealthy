var WeeklyUpdater = {};

WeeklyUpdater.Update = function() {
	for(var i = 0 ; i < Sensor.sensorArray.length; i++) {	
		WeeklyUpdater.UpdateChartWith(Sensor.sensorArray[i]);
	}
};

WeeklyUpdater.UpdateChartWith = function (databaseName) {
	var link = "/html/php/" + databaseName + ".php";
	var json = $.ajax({				 
		url: link,
		dataType: "json",
		success: function(jsonstring) {	
			var sensorData = WeeklyUpdater.GetChartData(jsonstring);
			WeeklyUpdater.DrawChart(sensorData, databaseName);
		},
		error: function(xhr, status, error) {					
			alert(error);
		}				
	}).responseText;			
};

WeeklyUpdater.GetChartData = function (jsonData) {
	var data = new google.visualization.DataTable();
	data.addColumn('datetime', 'Date');
	data.addColumn('number', 'Average');
	data.addColumn({type: 'string', role:'tooltip'}); 
	for(var i = 0; i < jsonData.length; i++) {		
		var t = DateJs.ConvertJSONToDateTimeObject(jsonData[i].Date);	
		if(t >= DateJs.GetFirstDayOfTheWeek(DateUpdater.current) && t <= DateJs.GetLastDayOfTheWeek(DateUpdater.current)) {
			data.addRow([t, Number(jsonData[i].Average), ("Date : " + DateJs.GetDateFromJSON(jsonData[i].Date) +
														  "\nAve : " + jsonData[i].Average + 
														  "\nMin : " + jsonData[i].Minimum + 
														  "\nMax : " + jsonData[i].Maximum)]);
		}
	}
	return data;
};

WeeklyUpdater.DrawChart = function(chartData, className) {
	var options = {		
		legend: { position: 'none'},
		backgroundColor: "transparent",
		hAxis: {
			gridlines: {color: '#333', count: 6},
			maxValue: DateJs.GetLastDayOfTheWeek(DateUpdater.current),
			minValue: DateJs.GetFirstDayOfTheWeek(DateUpdater.current)
		},
		vAxis: {
			title: className
		}
	};
	var chart = new google.visualization.LineChart(document.getElementById(className));
	chart.draw(chartData, options);
};