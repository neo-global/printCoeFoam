
    const cellList& cells = mesh.cells();
    const labelUList& own = mesh.owner();
    const labelUList& nei = mesh.neighbour();

    scalarField& Diag = UEqn.diag();
    forAll(cells, i)
    {
        if (UEqn.symmetric() || UEqn.asymmetric())
        {
            const cell& c = cells[i];
	    Info<<i<<endl;
          if (UEqn.symmetric())
	  {
            Info<<Diag[i]<<"\t:";
            forAll(c, j)
            {
                const label facei = c[j];

                if (mesh.isInternalFace(facei))
                {
                    Info<<UEqn.upper()[facei]<<"="; //= 0.0;
                   // if (UEqn.symmetric())
                    {
                        if (i == own[facei])
                        {
                            Info<<UEqn.source()[nei[facei]]<<endl; //-= UEqn.upper()[facei]*value;
                        }
                        else
                        {
                            Info<<UEqn.source()[own[facei]]<<endl; // -= UEqn.upper()[facei]*value;
                        }
                    }
	        }
	    }
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
                	const label facei = c[j];
                        if (i == own[facei])
                        {
                            Info<<"\t"<<UEqn.source()[nei[facei]]<<endl; //-= UEqn.lower()[facei]*value;
                        }
                        else
                        {
                            Info<<"\t"<<UEqn.source()[own[facei]]<<endl; //-= UEqn.upper()[facei]*value;
                        }
		}
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
