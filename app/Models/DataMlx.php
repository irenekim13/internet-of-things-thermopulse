<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class DataMlx extends Model
{
    use HasFactory;

    protected $fillable = [
        'id',
        'data_temperature',
        'data_saturasi',
        'data_denyut',
        'created_at',
        'updated_at'
    ];
}
