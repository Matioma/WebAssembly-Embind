class ExecutionTime{
    static TestTime(functionTest){
        let t0= performance.now(); //start time
        functionTest();
        let t1= performance.now(); //end time
        console.log(t1-t0, "miliSec");
    }
}