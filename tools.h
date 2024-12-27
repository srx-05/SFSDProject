#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED


//file weekly update function
void  update(const char *studentfile,const char *updatefile){
    FILE *f=fopen(studentfile,"r");
    FILE *upd=fopen(updatefile,"r");

    //make usre both files exist
    if (f==NULL){
    printf("ERROR, %s doesn't exist.\n",studentfile);
    exit(-1);
    }
    if (upd==NULL){
    printf("ERROR, %s doesn't exist.\n",updatefile);
    fclose(f);
    exit(-2);
    }

    time_t lastupd;
    if (fscanf(upd,"%ld",&lastupd)!=1){
        printf("ERROR, impossible to read from %s .\n",updatefile);
        fclose(upd);
        fclose(f);
        exit(-3);
    }

    time_t now=time(NULL);

    //check if the difference between now and last update date is a week
    if (difftime(now,lastupd)>=7*24*60*60){
        PhysicalDelet();
        printf("%s upddated successfully!\n",studentfile);
        fclose(upd);
        upd=fopen(updatefile,"w");
        if (upd==NULL){
            printf("ERROR, impossible to open %s for writing.\n",updatefile);
            fclose(f);
            exit(-4);
        }
        fprintf(upd,"%ld",now);
    }
    
    fclose(upd);
    fclose(f); 
}


#endif