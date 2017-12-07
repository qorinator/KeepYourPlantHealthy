var currentDisplay = new Date();
var todayDate = new Date();

function GetMonthString(month) {
	var monthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];	
	return monthNames[month];
}

window.onload = function() {	
	DisplayWeek(currentDisplay)
}

function DisplayWeek(date) {
	document.getElementById('weekDisplay').innerHTML = GetDisplayWeek(GetFirstDayOfTheWeek(date), GetLastDayOfTheWeek(date));
}

function GetFirstDayOfTheWeek(date) {
	var curr = new Date(date);
	var first = curr.getDate() - curr.getDay();
	return new Date(curr.setDate(first))
}

function GetLastDayOfTheWeek(date) {	
	var first = new Date(GetFirstDayOfTheWeek(date));
	var last = first.getDate() + 6;
	return new Date(first.setDate(last));
}

function GetDisplayWeek(first, last) {
	var output;

	if(first.getMonth() == last.getMonth()) {
		output = GetMonthString(first.getMonth()) + ' ' + first.getDate() + " - " + last.getDate() + ", " + first.getFullYear();
	}
	else if(first.getMonth() != last.getMonth()){
		output = GetMonthString(first.getMonth()) + ' ' + first.getDate() + " - " + 
				 GetMonthString(last.getMonth()) + ' ' + last.getDate() + ", " + first.getFullYear();
	}

	return output;
}

function PreviousWeek() {
	currentDisplay.setDate(currentDisplay.getDate() - 7);
	DisplayWeek(currentDisplay);
}
function NextWeek() {
	if(currentDisplay >= todayDate) {
		DisplayWeek(todayDate);
	}
	else {
		currentDisplay.setDate(currentDisplay.getDate() + 7);
		DisplayWeek(currentDisplay);
	}
}