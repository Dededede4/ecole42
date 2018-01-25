function displayFormContents() {

	var out = '';

	out += 'Firstname = ' + document.getElementById('firstname').value + '\n';
	out += 'Name = '      + document.getElementById('name').value      + '\n';
	out += 'Phone = '     + document.getElementById('phone').value     + '\n';
	out += 'Age = '       + document.getElementById('age').value       + '\n';
	out += 'Email = '     + document.getElementById('email').value     + '\n';

	out += 'Gender = ';
	if (document.getElementById('gender_male').checked == true)
		out += document.getElementById('gender_male').value;
	if (document.getElementById('gender_female').checked == true)
		out += document.getElementById('gender_female').value;
	if (document.getElementById('gender_other').checked == true)
		out += document.getElementById('gender_other').value;
	out += '\n';

	if (document.getElementById('student').checked == true)
		out += 'Student at 42 = yes';
	else
		out += 'Student at 42 = no';

	alert(out);

}
