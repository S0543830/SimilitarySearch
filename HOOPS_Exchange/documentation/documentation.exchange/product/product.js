function init() {
	$('.api-toggle').click(function(e) {
		//Handle the +/- button image clicks
		var divId = e.target.id.substring(0, e.target.id.length - '_link'.length + 1);
		
		document.getElementById(divId).style.display = (document.getElementById(divId).style.display == 'none') ? 'block' : 'none';	
	
		var imageElement = document.getElementById(divId + "_img");	
		imageElement.src = (imageElement.src.indexOf('plus.gif') >= 0) ? imageElement.src.replace('plus.gif', 'minus.gif') : imageElement.src.replace('minus.gif', 'plus.gif');
	
		e.preventDefault();
	});
}

/* This function brings the current tab and content in front */
function showCurrentTab(e) {
	var currTab = this;
	var tabGroup = this.parentNode;
	var tabs = tabGroup.getElementsByClassName("tabElement");
	
	for (var i = 0; i < tabs.length; ++i) {
		removeClassName(tabs[i], "currentTab");
	}

	addClassName(currTab, "currentTab")
	
	// Get the associated tabContent group so that we can find
	// code sample referred to by the href
	var divGroup = tabGroup.parentNode;
	var contents = divGroup.getElementsByClassName("tabContent");
	var anchor = currTab.getElementsByTagName("a")[0];
	var snippetType = getHash(anchor.href);
	showCurrentTabContent(contents, snippetType);

	return false; // prevent anchor events as well
}

/* show the associated code sample in the tab content list and hides the other code sample*/
function showCurrentTabContent(contents, snippetType) {
	if (contents.length === 0) {
		return;
	}
	var samples = contents[0].getElementsByClassName("codeSample");

	for (var i = 0; i < samples.length; ++i) {
		var sample = samples[i];
		if (hasClassName(sample, snippetType)) {
			removeClassName(sample, "hide");
		}
		else {
			addClassName(sample, "hide");
		}
	}
}



function constFunc(x) {
	return function () {
		return x;
	}
}

function getHash(url) {
	return url.substring(url.lastIndexOf("#") + 1);
}

function trim(str) {
	return str.replace(/^\s+/, "").replace(/\s+$/, "");
}

function condenseWs(str) {
	return str.replace(/\s+/g, " ");
}

function hasClassName(elt, className) {
	var pat = new RegExp("\\b" + className + "\\b");
	return pat.test(elt.className);
}

function addClassName(elt, className) {
	if (!hasClassName(elt, className)) {
		elt.className += " " + className;
	}
}

function removeClassName(elt, className) {
	var pat = new RegExp("\\b" + className + "\\b", "g");
	elt.className = trim(condenseWs(elt.className.replace(pat, "")));
}


function constFunc(x) {
	return function () {
		return x;
	}
}

function getHash(url) {
	return url.substring(url.lastIndexOf("#") + 1);
}

function trim(str) {
	return str.replace(/^\s+/, "").replace(/\s+$/, "");
}

function condenseWs(str) {
	return str.replace(/\s+/g, " ");
}

function hasClassName(elt, className) {
	var pat = new RegExp("\\b" + className + "\\b");
	return pat.test(elt.className);
}

function addClassName(elt, className) {
	if (!hasClassName(elt, className)) {
		elt.className += " " + className;
	}
}

function removeClassName(elt, className) {
	var pat = new RegExp("\\b" + className + "\\b", "g");
	elt.className = trim(condenseWs(elt.className.replace(pat, "")));
}

function cl_expcol(a)
{
	document.getElementById(a).style.display = (document.getElementById(a).style.display == 'none') ? 'block' : 'none';
	
	swap_exp_col_img(a);
}

function swap_exp_col_img(imgID)
{
	var e = document.getElementById(imgID + "_img");
	
	var backslashIndex = e.src.lastIndexOf('/');
	
	var filename = e.src.substring(backslashIndex);
	var path = e.src.substring(0, backslashIndex);
				
	if (filename == '/plus.gif')
		e.src = path + '/minus.gif';
	else
		e.src = path + '/plus.gif';
}

<!-- google custom search -->
  (function() {
    var cx = '013954542564809243169:sdg0qgwzml4';
    var gcse = document.createElement('script'); gcse.type = 'text/javascript'; gcse.async = true;
    gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
        '//www.google.com/cse/cse.js?cx=' + cx;
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(gcse, s);
  })();
<!-- end google custom search -->


