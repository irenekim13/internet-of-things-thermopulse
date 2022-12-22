<?php

namespace App\Http\Controllers;

use App\Models\DataMlx;
use Dflydev\DotAccessData\Data;
use Illuminate\Http\Request;

class DataMlxController extends Controller
{
    public function index(){
        $data = DataMlx::orderBy('id','desc')->get();

        return view('data_mlx')->with(['data' => $data]);
    }

    public function getData(){
        return ['data'=> 'tes'];
    }

    public function insertMlx(Request $r){
        return $r;
    }

    public function insertUltraMax(Request $r){
        return $r;
    }

    public function insertData(Request $r){
        
            DataMlx::create([
                'data_temperature' => $r->temperature,
                'data_saturasi' => $r->saturasi,
                'data_denyut' => $r->denyut,
            ]);
    
            return ['status'=> 'Berhasil'];
        
    }
}
