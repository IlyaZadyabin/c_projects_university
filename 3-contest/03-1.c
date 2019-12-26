int 
bitcount(STYPE value)
{
    int cnt = 0;
    UTYPE u_value = value;

    while(u_value) {
        cnt += (u_value) & 1;
        u_value >>= 1;
    }
    return cnt;
}
