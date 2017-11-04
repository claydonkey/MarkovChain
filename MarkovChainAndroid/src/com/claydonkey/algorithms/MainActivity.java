package com.claydonkey.algorithms;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.TextView.OnEditorActionListener;
import com.google.common.primitives.Doubles;
//import com.google.common.primitives.Doubles;
import java.text.DecimalFormat;


public class MainActivity extends Activity {

    /**
     * Called when the activity is first created.
     */
    private static final String TAG = "MainActivity";

    /**
     * Called when the activity is first created.
     *
     * @param savedInstanceState
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);

	/* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
	 */
	setContentView(R.layout.main);

	final EditText et_p = (EditText) findViewById(R.id.et_p);
	final EditText et_k = (EditText) findViewById(R.id.et_k);
	final EditText et_n = (EditText) findViewById(R.id.et_n);
	et_p.setOnEditorActionListener(new OnEditorActionListener() {
	    @Override
	    public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
		boolean handled = false;
		if (actionId == EditorInfo.IME_ACTION_SEND) {
		    GetProbability(Double.parseDouble(et_p.getText().toString()), Integer.parseInt(et_n.getText().toString()), Integer.parseInt(et_k.getText().toString()) );
		    handled = true;
		}
		return handled;
	    }




	});
    }

    private void GetProbability(double p, int n, int k) {
	DecimalFormat df = new DecimalFormat("#.######");
	String s = new String();
	TextView tv = (TextView) findViewById(R.id.tv_P);
	Iterable<Double> l = Doubles.asList(markovArrayResult(p,n,k));
	int i = 0;
	int dim = markovArrayDim();
	for (Double d : l) {
	    //    s += df.format(d) + " ";
	    s += (i % (dim * (dim - 1)) == 0 && i != 0) ? "Result: " + df.format(d) + "\n" : "";
	    i++;
	}

	//tv.setText(TextUtils.join(" ", l));
	tv.setText(s);

    }


    public native double[] markovArrayResult(double p, int n, int k);

    public native int markovArrayDim();

    /*
     * Trying to call this function will result in a
     * java.lang.UnsatisfiedLinkError exception !
     */
    public native String stringFromJNI();

    /* this is used to load the library on application
     * startup. The library has already been unpacked into
     * /data/data/com.claydonkey.algorithms/lib/libhello-jni.so at
     * installation time by the package manager.
     */
    static {
	System.loadLibrary("MarkovChain");
    }
}
