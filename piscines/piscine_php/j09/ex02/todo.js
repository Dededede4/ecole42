function aff(str)
{
	console.log(str);
	alert(str);
}
function delme(elem)
{
	elem.remove();
}
document.getElementById('new').onclick =function(){
	var text = prompt('Votre note :');
	if (text && text != '')
	{
		var input = document.createElement("div");
		input.innerHTML = text;
		input.setAttribute("onclick", "delme(this);");
		var mydiv = document.getElementById("ft_list");
		mydiv.prepend(input);
	}
}