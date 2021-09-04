     for(int c = 0; c < columnS; c++)
    {
        for(int r = 0; r < 3; r++)
        {
            if(com[r][c] > 120)
            {
                s[m] = '\0';
                break;
            }
            else
            {
                s[m] = com[r][c] + 97;
                m++;
            }
           
        }
    }
    s[m] = '\0';
    printf("%s\n",s);