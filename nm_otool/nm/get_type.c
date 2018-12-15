char	get_type(char *c, uint8_t n_sect)
{

}

char	get_type(struct nlist_64 el)
{
	char 	c;

	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
	{
		if (el.n_value)
			c = 'C'; // undefined, n_sect == NO_SECT
		else
			c = 'U';
	}
	else if (N_ABS == (el.n_type & N_TYPE))
		c = 'A'; // absolute, n_sect == NO_SECT
	else if (N_INDR == (el.n_type & N_TYPE))
		c = 'I'; // inderct
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
	else if (lookfor(el.n_sect, command.bss_numbers))
		c = 'B';
	else if (lookfor(el.n_sect, command.const_numbers))
		c = 'S';
	else if (lookfor(el.n_sect, command.data_numbers))
		c = 'D';
	else if (lookfor(el.n_sect, command.text_numbers))
		c = 'T';
	else
		c = '?';
	if ((0 != (el.n_type & N_EXT)))
		return (c);
	return (ft_tolower(c));
}

char	get_type_32(struct nlist el)
{
	t_bool upper;
	char 	c;

	upper = (0 != (el.n_type & N_EXT));

	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
	{
		if (el.n_value)
			c = 'C'; // undefined, n_sect == NO_SECT
		else
			c = 'U';
	}
	else if (N_ABS == (el.n_type & N_TYPE))
		c = 'A'; // absolute, n_sect == NO_SECT
	else if (N_INDR == (el.n_type & N_TYPE))
		c = 'I'; // inderct
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
	else if (lookfor(el.n_sect, command.bss_numbers))
		c = 'B';
	else if (lookfor(el.n_sect, command.const_numbers))
		c = 'S';
	else if (lookfor(el.n_sect, command.data_numbers))
		c = 'D';
	else if (lookfor(el.n_sect, command.text_numbers))
		c = 'T';
	else
		c = '?';
	if (upper)
		return (c);
	else
		return (ft_tolower(c));
}