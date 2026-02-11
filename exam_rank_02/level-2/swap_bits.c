unsigned char swap_bits(unsigned char octet)
{
	unsigned char res = 0;
	res = octet >> 4 | octet << 4;
	return (res);
}