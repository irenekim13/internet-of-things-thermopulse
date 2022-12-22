@extends('layout')
@section('content')

<div class="row">
    <div class="col-12">
    <div class="card">
        <!-- /.card-header -->
        <div class="card-body">
        <table id="example1" class="table table-bordered table-hover">
            <thead>
            <tr>
                <th width="1%">No</th>
                <th>Data Temperature</th>
                <th>Saturasi Oksigen</th>
                <th>Pulse</th>
                <th>Data Created</th>
            </tr>
            </thead>
            <tbody>
                @php
                    $no = 1;    
                @endphp
                @foreach ($data as $d)
                <tr>
                    <td>{{ $no++ }}</td>
                    <td>{{ $d->data_temperature }}</td>
                    <td>{{ $d->data_saturasi }}</td>
                    <td>{{ $d->data_denyut }}</td>
                    <td>{{ $d->created_at }}</td>
                </tr>
                @endforeach
            </body>
        </table>
        </div>
        <!-- /.card-body -->
    </div>
    <!-- /.card -->
    </div>
    <!-- /.col -->
</div>
<!-- /.row -->
@endsection