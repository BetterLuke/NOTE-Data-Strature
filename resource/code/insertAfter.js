function insertAfter(newElemant,targetElement) {
	var parent = targetElement.parentNode;
	if(targetElement == parent.lastChild) {
		parent.appendChild(newElemant);
	} else {
		parent.insertBefore(newElemant,targetElement.nextSilding);
	}
}