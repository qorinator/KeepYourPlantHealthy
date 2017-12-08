var SensorChartUpdater = {};

SensorChartUpdater.Update = function() {
	for(var i = 0 ; i < Sensor.sensorArray.length; i++) {	
		GetNextDatabase(Sensor.sensorArray[i]);
	}
};

function GetNextDatabase(dataB) {
	var link = "/html/php/" + dataB + ".php";
	var json = $.ajax({				 
		url: link,
		dataType: "json",
		success: function(jsonstring) {	
			var sensorData = SensorChartUpdater.GetChartData(jsonstring);
			SensorChartUpdater.DrawChart(sensorData, dataB);
		},
		error: function(xhr, status, error) {					
			alert(error);
		}				
	}).responseText;			
};

SensorChartUpdater.GetChartData = function (jsonData) {
	var data = new google.visualization.DataTable();
	data.addColumn('datetime', 'Date');
	data.addColumn('number', 'Average');
	data.addColumn({type: 'string', role:'tooltip'}); 
	for(var i = 0; i < jsonData.length; i++) {		
		var t = ChartUpdater.ConvertJSONToDateTimeObject(jsonData[i].Date);	
		if(t >= GetFirstDayOfTheWeek(currentDisplay) && t <= GetLastDayOfTheWeek(currentDisplay)) {
			data.addRow([t, Number(jsonData[i].Average), ("ave : " + jsonData[i].Average + 
														  "\nmin : " + jsonData[i].Minimum + 
														  "\nmax : " + jsonData[i].Maximum)]);
		}
	}
	return data;
};


SensorChartUpdater.DrawChart = function(chartData, className) {
	var options = {		
		legend: { position: 'none'},
		backgroundColor: "transparent",
		hAxis: {
			gridlines: {color: '#333', count: 6},
			// minorGridlines: {count: 2},
			maxValue: GetLastDayOfTheWeek(currentDisplay),
			minValue: GetFirstDayOfTheWeek(currentDisplay)
		},
		vAxis: {
			title: className
		}
	};
	var chart = new google.visualization.LineChart(document.getElementById(className));
	chart.draw(chartData, options);
};