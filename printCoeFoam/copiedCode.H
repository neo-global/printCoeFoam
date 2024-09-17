
    const cellList& cells = mesh.cells();
    const labelUList& own = mesh.owner();
    const labelUList& nei = mesh.neighbour();

    scalarField& Diag = UEqn.diag();

    int cellCount = cells.size();
    Info <<cellCount<<"x"<<cellCount<<" matrix needed."<<endl;
    scalarField rowI = UEqn.diag();

    forAll(cells, i)
    {
    	rowI = 0.0;
        if (UEqn.symmetric() || UEqn.asymmetric())
        {
          const cell& c = cells[i];
	  //Info<<i<<endl;
          if (UEqn.symmetric())
	  {
            forAll(c, j)
            {
                const label facei = c[j];
                if (mesh.isInternalFace(facei))
                {
                        if(i ==nei[facei])
                        {
		    	    rowI[own[facei]]= UEqn.upper()[facei];
		    	    //Info<<own[facei]<<":"<<UEqn.upper()[facei]<<"\t";
                	}
		}
	    }
            rowI[i]=Diag[i];
            //Info<<Diag[i]<<"\t";
	    forAll(c,j)
	    {
                const label facei = c[j];
                if (mesh.isInternalFace(facei))
                {
			if (i == own[facei]) //owner is the first id
                        {
		    	    rowI[nei[facei]]= UEqn.upper()[facei];
		    	    //Info<<nei[facei]<<":"<<UEqn.upper()[facei]<<"\t";
                        }
		}	
	    }
	    forAll(rowI,j)
	    {
		Info<<rowI[j]<<"\t";
	    }
	    Info<<endl;
	  }
          else //asymmetric
	  {
	      	forAll(c,j)
              	{
                	const label facei = c[j];
                        Info<<UEqn.lower()[facei]<<"\t"; //= 0.0;
              	}
              	Info<<Diag[i]<<"\t";
	      	forAll(c,j)
	      	{
                	const label facei = c[j];
                        Info<<UEqn.upper()[facei]<<"="; //= 0.0;
 	      	}	
	      	forAll(c,j)
	        {
			/*
                	const label facei = c[j];
                        if (i == own[facei])
                        {
                            Info<<"\t"<<UEqn.source()[nei[facei]]<<endl; //-= UEqn.lower()[facei]*value;
                        }
                        else
                        {
                            Info<<"\t"<<UEqn.source()[own[facei]]<<endl; //-= UEqn.upper()[facei]*value;
                        }
			*/
		}
		Info<<endl;
           }
	}
                else
                {
        /*
	            label patchi = mesh.boundaryMesh().whichPatch(facei);

                    if (internalCoeffs_[patchi].size())
                    {
	
                        label patchFacei =
                            mesh.boundaryMesh()[patchi].whichFace(facei);

                        internalCoeffs_[patchi][patchFacei] =
                            Zero;

                        boundaryCoeffs_[patchi][patchFacei] =
                            Zero;
                    }
	*/
                }
}
