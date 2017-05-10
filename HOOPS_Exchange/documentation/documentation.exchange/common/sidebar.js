$(document).ready(function($) {
	$('#accordion').find('.accordion-toggle').click(function(){
	  $(this).next().slideToggle(50);
	});
	
	var constFalse = constFunc(false);

	// add onclick handler for all tabElements
	var tabs = document.getElementsByClassName("tabElement");
	for (var i = 0; i < tabs.length; ++i) {
		var tab = tabs[i];
		tab.onclick = showCurrentTab;

		// prevent child anchors from modifying page's url
		var anchors = tab.getElementsByTagName("a");
		for (var j = 0; j < anchors.length; ++j) {
			anchors.onclick = constFalse;
		}
	}
	
	$('.api-toggle').click(function(e) {
		//Handle the +/- button image clicks
		var divId = e.target.id.substring(0, e.target.id.length - '_link'.length + 1);
		
		document.getElementById(divId).style.display = (document.getElementById(divId).style.display == 'none') ? 'block' : 'none';	
	
		var imageElement = document.getElementById(divId + "_img");	
		imageElement.src = (imageElement.src.indexOf('plus.gif') >= 0) ? imageElement.src.replace('plus.gif', 'minus.gif') : imageElement.src.replace('minus.gif', 'plus.gif');
	
		e.preventDefault();
	});
  });
  

function constFunc(x) {
	return function () {
		return x;
	}
}  