class Vector3{
    constructor(x,y,z){
        this.x = x;
        this.y = y;
        this.z = z;
    }
    Normalized(){
        let newVec = new Vector3(0,0,0);
        let magnitude = this.Magnitude();
        if(magnitude ==0) return vec;
        vec = this.Scale(1/magnitude);
        return vec;
    }
    Normalize(){
        let magnitude = this.Magnitude();
        if(magnitude == 0) return false;
    
        this.x = this.x*(1/magnitude);
        this.y = this.y*(1/magnitude);
        this.z = this.z* (1/magnitude);
        // this = this.Scale(1/magnitude);
        return true;
    }
    Magnitude(){
        return Math.sqrt(this.SqrMagnitude());
    }
    SqrMagnitude(){
        return (this.x*this.x) + (this.y*this.y) +(this.z*this.z);
    }
    Add(vector){
        if(!(vector instanceof Vector3)){
            console.error("Expected a object of Vector3 Type");
            return;
        }
        return new Vector3(this.x+vector.x, this.y+ vector.y, this.z+vector.z);
    }
    Subtract(vector){
        if(!(vector instanceof Vector3)){
            console.error("Expected a object of Vector3 Type");
            return;
        }
        return new Vector3(this.x-vector.x, this.y- vector.y, this.z-vector.z);
    }
    Scale(value){
        return new Vector3(this.x*value, this.y*value, this.z*value);
    }
    Set(vector){
        this.x = vector.x;
        this.y = vector.y;
        this.z = vector.z;
    }
    IsEqual(vector){
        if(!(vector instanceof Vector3)){
            console.error("Expected a object of Vector3 Type");
            return false;
        }
        return (this.x == vector.x && this.y == vector.y && this.z==vector.z);
    }
    static Dot(vector1, vector2){
        if(!(vector1 instanceof Vector3) || !(vector2 instanceof Vector3)){
            console.error("Expected both objects of Vector3 Type");
            return;
        }
        return (vector1.x * vector2.x + vector1.y*vector2.y + vector1.z*vector2.z);
    }
    static Cross(vector1, vector2){
        if(!(vector1 instanceof Vector3) || !(vector2 instanceof Vector3)){
            console.error("Expected both objects of Vector3 Type");
            return;
        }
        let newVec = new Vector3();
        newVec.x = vector1.y*vector2.z - vector1.z*vector2.y;
        newVec.y =vector1.z*vector2.x - vector1.x*vector2.z;
        newVec.z = vector1.x*vector2.y - vector1.y*vector2.x;
        return newVec;
    }
}