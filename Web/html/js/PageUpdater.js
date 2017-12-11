var PageUpdater = {};

PageUpdater.fileName = $('script[src*=PageUpdater]');
PageUpdater.choice = PageUpdater.fileName.attr('data-caller');

var x = 0;

window.onload = function() {
	PageUpdater.fileName = $('script[src*=PageUpdater]');
	PageUpdater.choice = PageUpdater.fileName.attr('data-caller');
	ContentUpdater.UpdateDateDisplay(PageUpdater.choice)
}

google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(function() {ContentUpdater.UpdateChart(PageUpdater.choice);});

$(window).resize(function() {
	ContentUpdater.UpdateChart(PageUpdater.choice);
});

PageUpdater.PreviousDay = function () {
	DateUpdater.DecreaseDate();	
	ContentUpdater.Update(PageUpdater.choice);
};

PageUpdater.NextDay = function() {
	DateUpdater.IncreaseDate();
	ContentUpdater.Update(PageUpdater.choice);
};

PageUpdater.PreviousWeek = function () {
	DateUpdater.DecreaseWeek();	
	ContentUpdater.Update(PageUpdater.choice);
};

PageUpdater.NextWeek = function() {
	DateUpdater.IncreaseWeek();
	ContentUpdater.Update(PageUpdater.choice);
};