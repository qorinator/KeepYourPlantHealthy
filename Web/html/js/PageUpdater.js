var PageUpdater = {};

PageUpdater.fileName = $('script[src*=PageUpdater]');
PageUpdater.choice = PageUpdater.fileName.attr('data-caller');

PageUpdater.Previous = function() {
	DateUpdater.Decrease(PageUpdater.choice);
	ContentUpdater.Update(PageUpdater.choice);
};

PageUpdater.Next = function() {
	DateUpdater.Increase(PageUpdater.choice);
	ContentUpdater.Update(PageUpdater.choice);
};

google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(function() {ContentUpdater.UpdateChart(PageUpdater.choice);});

window.onload = function() {
	PageUpdater.fileName = $('script[src*=PageUpdater]');
	PageUpdater.choice = PageUpdater.fileName.attr('data-caller');
	ContentUpdater.UpdateDateDisplay(PageUpdater.choice)
};

$(window).resize(function() {
	ContentUpdater.UpdateChart(PageUpdater.choice);
});