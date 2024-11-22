package IgniV;

/**
 * A simple object containing a type and value.
 */
public class EvalResult
{
    public EvalType type;
    public Object value;
    
    public EvalResult() {
    }

    public EvalResult(EvalType type, Object value) {
        this.type = type;
        this.value = value;
    }
    
    @Override
    public Object clone() {
        if (this.value.getClass() == Integer.class) {
            return new EvalResult(this.type, Integer.valueOf((Integer)this.value));
        }
        else if (this.value.getClass() == Double.class) {
            return new EvalResult(this.type, Double.valueOf((Double)this.value));
        }
        else if (this.value.getClass() == Character.class) {
                return new EvalResult(this.type, Character.valueOf((Character)this.value));
        }
        else if (this.value.getClass() == String.class) {
            return new EvalResult(this.type, String.valueOf((String)this.value));
        }
        else { // is array
            return new EvalResult(this.type, this.value);
        }
        
        
    }
//    @Override
//    public Object clone(){
//        try{
//            return (EvalResult) super.clone();
//        }catch (CloneNotSupportedException e){
//            return new EvalResult(this.type, this.value);
//        }
//    }
}
