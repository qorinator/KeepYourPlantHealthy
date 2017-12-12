var MonthlyUpdater = {};

MonthlyUpdater.Update = function() {
	for(var i = 0 ; i < Sensor.sensorArray.length; i++) {
		MonthlyUpdater.UpdateChartWith(Sensor.sensorArray[i]);
	}
};

MonthlyUpdater.UpdateChartWith = function (databaseName) {
	var link = "/html/php/" + databaseName + ".php";
	var json = $.ajax({				 
		url: link,
		dataType: "json",
		success: function(jsonstring) {	
			var sensorData = MonthlyUpdater.GetChartData(jsonstring);
			MonthlyUpdater.DrawChart(sensorData, databaseName);
		},
		error: function(xhr, status, error) {
			alert(error);
		}				
	}).responseText;			
};

MonthlyUpdater.GetChartData = function (jsonData) {
	var data = new google.visualization.DataTable();
	data.addColumn('datetime', 'Date');
	data.addColumn('number', 'Average');
	data.addColumn({type: 'string', role:'tooltip'}); 
	for(var i = 0; i < jsonData.length; i++) {		
		var t = DateJs.ConvertJSONToDateTimeObject(jsonData[i].Date);
		if(t.getMonth() == DateUpdater.current.getMonth()) {
			data.addRow([t, Number(jsonData[i].Average), ("Date : " + DateJs.GetDateFromJSON(jsonData[i].Date) +
														  "\nAve : " + jsonData[i].Average + 
														  "\nMin : " + jsonData[i].Minimum + 
														  "\nMax : " + jsonData[i].Maximum)]);
		}
	}
	return data;
};

MonthlyUpdater.DrawChart = function(chartData, className) {	
	var options = {		
		legend: { position: 'none'},
		backgroundColor: "transparent",
		hAxis: {
			minorGridlines: {count: 6},
			gridlines: {color: '#333'},			
			maxValue: DateJs.GetLastDateOfTheMonth(DateUpdater.current),
			minValue: new Date(DateUpdater.current.getFullYear(), 
							   (DateUpdater.current.getMonth()), 
							    1, 0, 0, 0),
			ticks: MonthlyUpdater.GetTickMarks()
		},
		vAxis: {
			title: className
		}
	};
	var chart = new google.visualization.LineChart(document.getElementById(className));
	chart.draw(chartData, options);
};

MonthlyUpdater.GetTickMarks = function () {
	var tickMarks = [];
	var curr = new Date(DateUpdater.current.getFullYear(), DateUpdater.current.getMonth(), 1, 0, 0, 0);	
	var last = DateJs.GetLastDateOfTheMonth(DateUpdater.current);
	while(curr <= last) {
		if(curr.getDay() == 1)
			tickMarks.push(new Date(curr));
		curr.setDate(curr.getDate() + 1);
	}
	return tickMarks;
};