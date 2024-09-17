
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
        rowI[i]=Diag[i];

        const cell& c = cells[i];
	{
            forAll(c, j)
            {
                const label facei = c[j];
                if (mesh.isInternalFace(facei))
                {
                	if(i ==nei[facei])
                         {
		    	    rowI[own[facei]]= UEqn.upper()[facei];
                         }
                         else
                         {
		    	    rowI[nei[facei]]= UEqn.lower()[facei];
                         }
		}
	    }
	  }
	//Add boundary contributions.
	
	//print to console, or print to file.
	forAll(rowI,j)
	{
		Info<<rowI[j]<<"\t";
	}
	Info<<endl;
    }
 
