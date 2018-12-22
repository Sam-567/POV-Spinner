
public class All {
	
	int[][] Zero = { { 1, 1, 1},
			  		 { 1, 0, 1},
			  		 { 1, 0, 1},
			  		 { 1, 0, 1},
			  		 { 1, 1, 1} };
	
	int[][] One = { { 0, 1, 0},
	                { 1, 1, 0},
	                { 0, 1, 0},
	                { 0, 1, 0},
	                { 1, 1, 1} };

	int[][] Two = { { 0, 1, 0},
            		{ 1, 0, 1},
            		{ 0, 0, 1},
            		{ 0, 1, 0},
            		{ 1, 1, 1} };

	int[][] Three = { { 1, 1, 1},
    				  { 0, 0, 1},
    				  { 1, 1, 1},
    				  { 0, 0, 1},
    				  { 1, 1, 1} };
	
	int[][] Four = { { 1, 0, 1},
			  		 { 1, 0, 1},
			  		 { 1, 1, 1},
			  		 { 0, 0, 1},
			  		 { 0, 0, 1} };
	
	int[][] Five = { { 1, 1, 1},
					 { 1, 0, 0},
					 { 1, 1, 1},
					 { 0, 0, 1},
					 { 1, 1, 1} };

	int[][] Six = { { 1, 1, 1},
			 		{ 1, 0, 0},
			 		{ 1, 1, 1},
			 		{ 1, 0, 1},
			 		{ 1, 1, 1} };
	
	int[][] Seven = { { 1, 1, 1},
	 				  { 0, 0, 1},
	 				  { 0, 0, 1},
	 				  { 0, 0, 1},
	 				  { 0, 0, 1} };
	
	int[][] Eight = { { 1, 1, 1},
	 				  { 1, 0, 1},
	 				  { 1, 1, 1},
	 				  { 1, 0, 1},
	 				  { 1, 1, 1} };
	
	int[][] Nine = { { 1, 1, 1},
			  		 { 1, 0, 1},
			  		 { 1, 1, 1},
			  		 { 0, 0, 1},
			  		 { 1, 1, 1} };
	
	int[][] Colon = { { 0, 0, 0},
            		  { 0, 1, 0},
            		  { 0, 0, 0},
            		  { 0, 1, 0},
            		  { 0, 0, 0} };		
	
	int[][][] Numbers = {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};
	
	void DisplayTime( int hour, int minute){
		//Low min
		int LowMin = minute % 10;
		int HighMin = minute / 10;
		int LowHour = hour % 10;
		int HighHour = hour / 10;
		
		for(int i = 2; i >= 0; i--) {
			
			delay(2);
		}
		
		for(int i = 2; i >= 0; i--) {
			
			delay(2)
		}
		
		for(int i = 2; i >= 0; i--) {
			
			delay(2)
		}
		
		for(int i = 2; i >= 0; i--) {
			
			delay(2)
		}
		
	}
}
